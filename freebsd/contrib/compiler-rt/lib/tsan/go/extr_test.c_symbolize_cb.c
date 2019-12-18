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

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 void* current_proc ; 

void symbolize_cb(long cmd, void *ctx) {
  switch (cmd) {
  case 0:
    if (current_proc == 0)
      abort();
    *(void**)ctx = current_proc;
  }
}