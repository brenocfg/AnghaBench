#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* atf_error_t ;
struct TYPE_4__ {int m_free; struct TYPE_4__* m_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int) ; 
 int error_on_flight ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
atf_error_free(atf_error_t err)
{
    bool freeit;

    PRE(error_on_flight);
    PRE(err != NULL);

    freeit = err->m_free;

    if (err->m_data != NULL)
        free(err->m_data);

    if (freeit)
        free(err);

    error_on_flight = false;
}