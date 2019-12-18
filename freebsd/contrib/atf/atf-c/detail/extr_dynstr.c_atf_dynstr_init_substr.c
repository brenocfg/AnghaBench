#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  atf_error_t ;
struct TYPE_5__ {size_t m_length; scalar_t__ m_data; } ;
typedef  TYPE_1__ atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_dynstr_init_raw (TYPE_1__*,scalar_t__,size_t) ; 
 size_t atf_dynstr_npos ; 

atf_error_t
atf_dynstr_init_substr(atf_dynstr_t *ad, const atf_dynstr_t *src,
                       size_t beg, size_t end)
{
    if (beg > src->m_length)
        beg = src->m_length;

    if (end == atf_dynstr_npos || end > src->m_length)
        end = src->m_length;

    return atf_dynstr_init_raw(ad, src->m_data + beg, end - beg);
}