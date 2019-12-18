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
struct TYPE_3__ {size_t m_datasize; char* m_data; size_t m_length; } ;
typedef  TYPE_1__ atf_dynstr_t ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 

atf_error_t
atf_dynstr_init_rep(atf_dynstr_t *ad, size_t len, char ch)
{
    atf_error_t err;

    if (len == SIZE_MAX) {
        err = atf_no_memory_error();
        goto out;
    }

    ad->m_datasize = (len + 1) * sizeof(char);
    ad->m_data = (char *)malloc(ad->m_datasize);
    if (ad->m_data == NULL) {
        err = atf_no_memory_error();
        goto out;
    }

    memset(ad->m_data, ch, len);
    ad->m_data[len] = '\0';
    ad->m_length = len;
    err = atf_no_error();

out:
    return err;
}