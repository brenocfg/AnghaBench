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
struct TYPE_3__ {char* m_data; int m_datasize; scalar_t__ m_length; } ;
typedef  TYPE_1__ atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 scalar_t__ malloc (int) ; 

atf_error_t
atf_dynstr_init(atf_dynstr_t *ad)
{
    atf_error_t err;

    ad->m_data = (char *)malloc(sizeof(char));
    if (ad->m_data == NULL) {
        err = atf_no_memory_error();
        goto out;
    }

    ad->m_data[0] = '\0';
    ad->m_datasize = 1;
    ad->m_length = 0;
    err = atf_no_error();

out:
    return err;
}