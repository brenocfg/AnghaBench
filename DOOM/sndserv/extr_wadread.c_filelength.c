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
struct stat {int st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 

int filelength (int handle)
{
    struct stat	fileinfo;
  
    if (fstat (handle,&fileinfo) == -1)
	fprintf (stderr, "Error fstating\n");

    return fileinfo.st_size;
}