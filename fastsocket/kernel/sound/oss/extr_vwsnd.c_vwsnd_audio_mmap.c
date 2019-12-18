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
struct vm_area_struct {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGE (char*,struct file*,struct vm_area_struct*) ; 
 int ENODEV ; 

__attribute__((used)) static int vwsnd_audio_mmap(struct file *file, struct vm_area_struct *vma)
{
	DBGE("(file=0x%p, vma=0x%p)\n", file, vma);
	return -ENODEV;
}