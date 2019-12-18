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
typedef  size_t u32 ;

/* Variables and functions */
 size_t MAX_FILE_MODE ; 
 int /*<<< orphan*/  PARANOIA (char*,size_t) ; 
 int S_IFREG ; 
 int* file_mode ; 

__attribute__((used)) static int smb_filetype_to_mode(u32 filetype)
{
	if (filetype > MAX_FILE_MODE) {
		PARANOIA("Filetype out of range: %d\n", filetype);
		return S_IFREG;
	}
	return file_mode[filetype];
}