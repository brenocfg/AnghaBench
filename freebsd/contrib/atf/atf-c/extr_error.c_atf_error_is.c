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
typedef  TYPE_1__* atf_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  m_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

bool
atf_error_is(const atf_error_t err, const char *type)
{
    PRE(err != NULL);

    return strcmp(err->m_type, type) == 0;
}