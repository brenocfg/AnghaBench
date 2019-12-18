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
struct frame_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_CONVERT_TO_RAW (struct type*,int,char*,char*) ; 
 int MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_frame_register (struct frame_info*,int,char*) ; 

void
legacy_value_to_register (struct frame_info *frame, int regnum,
			  struct type *type, const void *tmp)
{
  char to[MAX_REGISTER_SIZE];
  char *from = alloca (TYPE_LENGTH (type));
  memcpy (from, from, TYPE_LENGTH (type));
  DEPRECATED_REGISTER_CONVERT_TO_RAW (type, regnum, from, to);
  put_frame_register (frame, regnum, to);
}