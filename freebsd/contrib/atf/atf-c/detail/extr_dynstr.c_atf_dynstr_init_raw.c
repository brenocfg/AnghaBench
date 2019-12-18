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
struct TYPE_3__ {char* m_data; size_t m_datasize; size_t m_length; } ;
typedef  TYPE_1__ atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int) ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 size_t strlen (char*) ; 

atf_error_t
atf_dynstr_init_raw(atf_dynstr_t *ad, const void *mem, size_t memlen)
{
    atf_error_t err;

    if (memlen >= SIZE_MAX - 1) {
        err = atf_no_memory_error();
        goto out;
    }

    ad->m_data = (char *)malloc(memlen + 1);
    if (ad->m_data == NULL) {
        err = atf_no_memory_error();
        goto out;
    }

    ad->m_datasize = memlen + 1;
    memcpy(ad->m_data, mem, memlen);
    ad->m_data[memlen] = '\0';
    ad->m_length = strlen(ad->m_data);
    INV(ad->m_length <= memlen);
    err = atf_no_error();

out:
    return err;
}