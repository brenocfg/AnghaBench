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
typedef  int /*<<< orphan*/  SESSION ;
typedef  int /*<<< orphan*/  SECURE_SIGN ;
typedef  int /*<<< orphan*/  CONNECTION ;

/* Variables and functions */
 int CncSecureSignDlg (int /*<<< orphan*/ *) ; 

bool CiSecureSignProc(SESSION *s, CONNECTION *c, SECURE_SIGN *sign)
{
	// The UI is available in Win32
	return CncSecureSignDlg(sign);
}