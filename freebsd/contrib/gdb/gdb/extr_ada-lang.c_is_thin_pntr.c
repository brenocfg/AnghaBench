#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ada_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_base_type (struct type*) ; 
 scalar_t__ is_suffix (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
is_thin_pntr (struct type *type)
{
  return
    is_suffix (ada_type_name (desc_base_type (type)), "___XUT")
    || is_suffix (ada_type_name (desc_base_type (type)), "___XUT___XVE");
}