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
typedef  int /*<<< orphan*/  EmscriptenPointerlockChangeEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  report_result (int) ; 

EM_BOOL pointerlockchange_callback(int eventType, const EmscriptenPointerlockChangeEvent *e, void *userData) {
  printf("ERROR! received 'pointerlockchange' event\n");
  report_result(1);

  return 0;
}