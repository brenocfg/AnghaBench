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
typedef  int /*<<< orphan*/  CURLUcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLUE_MALFORMED_INPUT ; 
 int /*<<< orphan*/  CURLUE_OK ; 
 size_t strcspn (char*,char const*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static CURLUcode junkscan(char *part)
{
  if(part) {
    static const char badbytes[]={
      /* */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
      0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
      0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
      0x7f,
      0x00 /* zero terminate */
    };
    size_t n = strlen(part);
    size_t nfine = strcspn(part, badbytes);
    if(nfine != n)
      /* since we don't know which part is scanned, return a generic error
         code */
      return CURLUE_MALFORMED_INPUT;
  }
  return CURLUE_OK;
}