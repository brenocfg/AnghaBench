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
 int MAX_REGISTER_SIZE ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  alpha_sts (void*,char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  frame_register_read (struct frame_info*,int,char*) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 

__attribute__((used)) static void
alpha_register_to_value (struct frame_info *frame, int regnum,
			 struct type *valtype, void *out)
{
  char in[MAX_REGISTER_SIZE];
  frame_register_read (frame, regnum, in);
  switch (TYPE_LENGTH (valtype))
    {
    case 4:
      alpha_sts (out, in);
      break;
    case 8:
      memcpy (out, in, 8);
      break;
    default:
      error ("Cannot retrieve value from floating point register");
    }
}