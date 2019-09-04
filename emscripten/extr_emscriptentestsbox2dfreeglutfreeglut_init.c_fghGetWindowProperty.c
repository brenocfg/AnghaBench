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
typedef  int /*<<< orphan*/  Window ;
struct TYPE_2__ {int /*<<< orphan*/  Display; } ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  FREEGLUT_INTERNAL_ERROR_EXIT (int,char*,char*) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int Success ; 
 int XGetWindowProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int*,unsigned long*,unsigned long*,unsigned char**) ; 
 TYPE_1__ fgDisplay ; 

__attribute__((used)) static int fghGetWindowProperty(Window window,
				Atom property,
				Atom type,
				unsigned char ** data)
{
  /*
   * Caller always has to use "Xfree()" to free "data", since
   * "XGetWindowProperty() always allocates one extra byte in prop_return
   * [i.e. "data"] (even if the property is zero length) [..]".
   */

  int status;  /*  Returned by "XGetWindowProperty". */

  Atom          type_returned;
  int           temp_format;             /*  Not used. */
  unsigned long number_of_elements;
  unsigned long temp_bytes_after;        /*  Not used. */


  status = XGetWindowProperty(fgDisplay.Display,
			      window,
			      property,
			      0,
			      LONG_MAX,
			      False,
			      type,
			      &type_returned,
			      &temp_format,
			      &number_of_elements,
			      &temp_bytes_after,
			      data);

  FREEGLUT_INTERNAL_ERROR_EXIT(status == Success,
			       "XGetWindowProperty failled",
			       "fghGetWindowProperty");

  if (type_returned != type)
    {
      number_of_elements = 0;
    }

  return number_of_elements;
}