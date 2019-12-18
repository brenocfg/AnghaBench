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
struct TYPE_2__ {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUSH_SPELLING (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPELLING_STRING ; 
 TYPE_1__ u ; 

__attribute__((used)) static void
push_string (const char *string)
{
  PUSH_SPELLING (SPELLING_STRING, string, u.s);
}