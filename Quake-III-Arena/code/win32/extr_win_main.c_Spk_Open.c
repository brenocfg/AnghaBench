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
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int S_IREAD ; 
 int S_IWRITE ; 
 int /*<<< orphan*/  fh ; 
 int /*<<< orphan*/  open (char*,int,int) ; 

void Spk_Open(char *name)
{
  fh = open( name, O_TRUNC | O_CREAT | O_WRONLY, S_IREAD | S_IWRITE );
}