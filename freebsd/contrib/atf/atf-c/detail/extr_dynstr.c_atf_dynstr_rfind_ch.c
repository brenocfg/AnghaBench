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
struct TYPE_3__ {size_t m_length; char* m_data; } ;
typedef  TYPE_1__ atf_dynstr_t ;

/* Variables and functions */
 size_t atf_dynstr_npos ; 

size_t
atf_dynstr_rfind_ch(const atf_dynstr_t *ad, char ch)
{
    size_t pos;

    for (pos = ad->m_length; pos > 0 && ad->m_data[pos - 1] != ch; pos--)
        ;

    return pos == 0 ? atf_dynstr_npos : pos - 1;
}