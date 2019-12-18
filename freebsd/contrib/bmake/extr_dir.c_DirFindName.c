#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static int
DirFindName(const void *p, const void *dname)
{
    return (strcmp(((const Path *)p)->name, dname));
}