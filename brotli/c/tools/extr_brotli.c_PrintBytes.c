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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void PrintBytes(size_t value) {
  if (value < 1024) {
    fprintf(stderr, "%d B", (int)value);
  } else if (value < 1048576) {
    fprintf(stderr, "%0.3f KiB", (double)value / 1024.0);
  } else if (value < 1073741824) {
    fprintf(stderr, "%0.3f MiB", (double)value / 1048576.0);
  } else {
    fprintf(stderr, "%0.3f GiB", (double)value / 1073741824.0);
  }
}