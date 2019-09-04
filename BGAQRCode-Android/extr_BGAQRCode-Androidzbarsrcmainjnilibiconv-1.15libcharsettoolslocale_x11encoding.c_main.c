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
struct TYPE_3__ {int format; scalar_t__ nitems; int /*<<< orphan*/  encoding; } ;
typedef  TYPE_1__ XTextProperty ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 scalar_t__ Success ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 char* XGetAtomName (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XTextStyle ; 
 scalar_t__ XmbTextListToTextProperty (int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int main (int argc, char* argv[])
{
  Display* display;
  XTextProperty textprop;
  char* input;

  if (argc != 1)
    exit(1);

  setlocale(LC_CTYPE,"");

  display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr,"cannot open display\n");
    exit(1);
  }

  input = "";
  if (XmbTextListToTextProperty(display, &input, 1, XTextStyle, &textprop) != Success) {
    fprintf(stderr,"XmbTextListToTextProperty failed\n");
    exit(1);
  }
  assert(textprop.format == 8);
  assert(textprop.nitems == 0);

  printf("%s\n", XGetAtomName(display, textprop.encoding));

  XCloseDisplay(display);

  exit(0);
}