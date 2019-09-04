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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  create_file (char*,char*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 

void setup() {
  create_file("test-file", "abcdef", 0777);
  mkdir("test-folder", 0777);
  assert(!errno);
}