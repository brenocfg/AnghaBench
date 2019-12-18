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
 unsigned int ASCII_CCSID ; 
 int /*<<< orphan*/  ICONV_ID_SIZE ; 
 unsigned int NOCONV_CCSID ; 
 int /*<<< orphan*/  curl_msprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
makeOS400IconvCode(char buf[ICONV_ID_SIZE], unsigned int ccsid)

{
  /**
  *** Convert a CCSID to the corresponding IBM iconv_open() character
  ***  code identifier.
  ***  This code is specific to the OS400 implementation of the iconv library.
  ***  CCSID 65535 (no conversion) is replaced by the ASCII CCSID.
  ***  CCSID 0 is interpreted by the OS400 as the job's CCSID.
  **/

  ccsid &= 0xFFFF;

  if(ccsid == NOCONV_CCSID)
    ccsid = ASCII_CCSID;

  memset(buf, 0, ICONV_ID_SIZE);
  curl_msprintf(buf, "IBMCCSID%05u0000000", ccsid);
}