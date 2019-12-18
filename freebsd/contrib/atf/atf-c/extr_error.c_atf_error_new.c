#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* atf_error_t ;
struct TYPE_9__ {int m_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POST (int) ; 
 int /*<<< orphan*/  PRE (int) ; 
 TYPE_1__* atf_no_memory_error () ; 
 int /*<<< orphan*/  error_init (TYPE_1__*,char const*,void*,size_t,void (*) (TYPE_1__* const,char*,size_t)) ; 
 int error_on_flight ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 

atf_error_t
atf_error_new(const char *type, void *data, size_t datalen,
              void (*format)(const atf_error_t, char *, size_t))
{
    atf_error_t err;

    PRE(!error_on_flight);
    PRE(data != NULL || datalen == 0);
    PRE(datalen != 0 || data == NULL);

    err = malloc(sizeof(*err));
    if (err == NULL)
        err = atf_no_memory_error();
    else {
        if (!error_init(err, type, data, datalen, format)) {
            free(err);
            err = atf_no_memory_error();
        } else {
            err->m_free = true;
            error_on_flight = true;
        }
    }

    INV(err != NULL);
    POST(error_on_flight);
    return err;
}