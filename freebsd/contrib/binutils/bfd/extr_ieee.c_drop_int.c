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
struct output_buffer_struct {int /*<<< orphan*/  buffer; int /*<<< orphan*/  ptrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  OUT (int) ; 
 int THIS () ; 
 int /*<<< orphan*/  output_buffer ; 
 int /*<<< orphan*/  output_ptr ; 

__attribute__((used)) static void
drop_int (struct output_buffer_struct *buf)
{
  int type = THIS ();
  int ch;

  if (type <= 0x84)
    {
      NEXT ();
      switch (type)
	{
	case 0x84:
	  ch = THIS ();
	  NEXT ();
	case 0x83:
	  ch = THIS ();
	  NEXT ();
	case 0x82:
	  ch = THIS ();
	  NEXT ();
	case 0x81:
	  ch = THIS ();
	  NEXT ();
	case 0x80:
	  break;
	}
    }
  OUT (0x84);
  buf->ptrp = output_ptr;
  buf->buffer = output_buffer;
  OUT (0);
  OUT (0);
  OUT (0);
  OUT (0);
}