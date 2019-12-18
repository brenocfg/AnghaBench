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
typedef  int umode_t ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG2 ; 
 int SET_FILE_EXEC_RIGHTS ; 
 int SET_FILE_READ_RIGHTS ; 
 int SET_FILE_WRITE_RIGHTS ; 
 int S_IRUGO ; 
 int S_IWUGO ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  cFYI (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void mode_to_access_flags(umode_t mode, umode_t bits_to_use,
				__u32 *pace_flags)
{
	/* reset access mask */
	*pace_flags = 0x0;

	/* bits to use are either S_IRWXU or S_IRWXG or S_IRWXO */
	mode &= bits_to_use;

	/* check for R/W/X UGO since we do not know whose flags
	   is this but we have cleared all the bits sans RWX for
	   either user or group or other as per bits_to_use */
	if (mode & S_IRUGO)
		*pace_flags |= SET_FILE_READ_RIGHTS;
	if (mode & S_IWUGO)
		*pace_flags |= SET_FILE_WRITE_RIGHTS;
	if (mode & S_IXUGO)
		*pace_flags |= SET_FILE_EXEC_RIGHTS;

	cFYI(DBG2, "mode: 0x%x, access flags now 0x%x", mode, *pace_flags);
	return;
}