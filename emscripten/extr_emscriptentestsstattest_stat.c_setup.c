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
struct utimbuf {int member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_file (char*,char*,int) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  symlink (char*,char*) ; 
 int /*<<< orphan*/  utime (char*,struct utimbuf*) ; 

void setup() {
  struct utimbuf t = {1200000000, 1200000000};
  
  mkdir("folder", 0777);
  create_file("folder/file", "abcdef", 0777);
  symlink("file", "folder/file-link");

  utime("folder/file", &t);
  utime("folder", &t);
}