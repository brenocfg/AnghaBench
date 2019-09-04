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
 int /*<<< orphan*/  create_file (char*,char*,int) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 

void setup() {
  create_file("file", "abcdef", 0777);
  mkdir("dir", 0777);
  create_file("dir/file", "abcdef", 0777);
  mkdir("dir/subdir", 0777);
  mkdir("dir-readonly", 0555);
  mkdir("dir-nonempty", 0777);
  mkdir("dir/subdir3", 0777);
  mkdir("dir/subdir3/subdir3_1", 0777);
  create_file("dir-nonempty/file", "abcdef", 0777);
}