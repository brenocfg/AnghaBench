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
 int mkdir (char*,int) ; 

void setup() {
  int err;
  err = mkdir("nocanread", 0111);
  assert(!err);
  err = mkdir("foobar", 0777);
  assert(!err);
  create_file("foobar/file.txt", "ride into the danger zone", 0666);
}