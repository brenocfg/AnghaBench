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
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_name; int /*<<< orphan*/  p_comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
process_name(const char *s, proc_t p)
{
       strlcpy(p->p_comm, s, sizeof(p->p_comm));
       strlcpy(p->p_name, s, sizeof(p->p_name));
}