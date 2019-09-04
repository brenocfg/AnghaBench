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
 int /*<<< orphan*/  lchmod (char*,int) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  symlink (char*,char*) ; 

void setup() {
  create_file("file", "abcdef", 0777);
  symlink("file", "file-link");
  // some platforms use 777, some use 755 by default for symlinks
  // make sure we're using 777 for the test
  lchmod("file-link", 0777);
  mkdir("folder", 0777);
}