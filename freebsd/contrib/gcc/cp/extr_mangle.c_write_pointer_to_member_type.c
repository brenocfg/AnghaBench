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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_POINTED_TO_TYPE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_pointer_to_member_type (const tree type)
{
  write_char ('M');
  write_type (TYPE_PTRMEM_CLASS_TYPE (type));
  write_type (TYPE_PTRMEM_POINTED_TO_TYPE (type));
}