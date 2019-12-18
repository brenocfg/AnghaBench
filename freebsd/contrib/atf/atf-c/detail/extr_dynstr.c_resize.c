#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  atf_error_t ;
struct TYPE_3__ {size_t m_datasize; char* m_data; } ;
typedef  TYPE_1__ atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static
atf_error_t
resize(atf_dynstr_t *ad, size_t newsize)
{
    char *newdata;
    atf_error_t err;

    PRE(newsize > ad->m_datasize);

    newdata = (char *)malloc(newsize);
    if (newdata == NULL) {
        err = atf_no_memory_error();
    } else {
        strcpy(newdata, ad->m_data);
        free(ad->m_data);
        ad->m_data = newdata;
        ad->m_datasize = newsize;
        err = atf_no_error();
    }

    return err;
}