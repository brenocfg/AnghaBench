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
typedef  int /*<<< orphan*/  tocode ;
typedef  int /*<<< orphan*/  iconv_t ;

/* Variables and functions */
 int ICONV_ID_SIZE ; 
 int /*<<< orphan*/  iconv_open (char*,char*) ; 
 int /*<<< orphan*/  makeOS400IconvCode (char*,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static iconv_t
iconv_open_CCSID(unsigned int ccsidout, unsigned int ccsidin,
                                                        unsigned int cstr)

{
  char fromcode[ICONV_ID_SIZE];
  char tocode[ICONV_ID_SIZE];

  /**
  ***  Like iconv_open(), but character codes are given as CCSIDs.
  ***  If `cstr' is non-zero, conversion is set up to stop whenever a
  ***   null character is encountered.
  ***  See iconv_open() IBM description in "National Language Support API".
  **/

  makeOS400IconvCode(fromcode, ccsidin);
  makeOS400IconvCode(tocode, ccsidout);
  memset(tocode + 13, 0, sizeof(tocode) - 13);   /* Dest. code id format. */

  if(cstr)
    fromcode[18] = '1';                         /* Set null-terminator flag. */

  return iconv_open(tocode, fromcode);
}