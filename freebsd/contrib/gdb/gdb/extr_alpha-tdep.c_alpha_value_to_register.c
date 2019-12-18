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
 int /*<<< orphan*/  alpha_lds (char*,void const*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 int /*<<< orphan*/  put_frame_register (struct frame_info*,int,char*) ; 

__attribute__((used)) static void
alpha_value_to_register (struct frame_info *frame, int regnum,
			 struct type *valtype, const void *in)
{
  char out[MAX_REGISTER_SIZE];
  switch (TYPE_LENGTH (valtype))
    {
    case 4:
      alpha_lds (out, in);
      break;
    case 8:
      memcpy (out, in, 8);
      break;
    default:
      error ("Cannot store value in floating point register");
    }
  put_frame_register (frame, regnum, out);
}