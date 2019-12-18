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
typedef  int /*<<< orphan*/  word ;
typedef  scalar_t__ byte ;

/* Variables and functions */
 int /*<<< orphan*/  ESC ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static word SuperTraceCreateReadReq (byte* P, const char* path) {
	byte var_length;
	byte* plen;

	var_length = (byte)strlen (path);

	*P++ = ESC;
	plen = P++;
	*P++ = 0x80; /* MAN_IE */
	*P++ = 0x00; /* Type */
	*P++ = 0x00; /* Attribute */
	*P++ = 0x00; /* Status */
	*P++ = 0x00; /* Variable Length */
	*P++ = var_length;
	memcpy (P, path, var_length);
	P += var_length;
	*plen = var_length + 0x06;

	return ((word)(var_length + 0x08));
}