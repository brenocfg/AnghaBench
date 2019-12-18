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
 char* HEX_FMT_STR ; 
 int HEX_STR_LEN ; 
 int NOTHING_LEN ; 
 char NOTHING_STR ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  msnprintf (char*,size_t,char*,char) ; 
 char* realloc (char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *printable(char *inbuf, size_t inlength)
{
  char *outbuf;
  char *newbuf;
  size_t newsize;
  size_t outsize;
  size_t outincr = 0;
  size_t i, o = 0;

#define HEX_FMT_STR  "[0x%02X]"
#define HEX_STR_LEN  6
#define NOTHING_STR  "[NOTHING]"
#define NOTHING_LEN  9

  if(!inlength)
    inlength = strlen(inbuf);

  if(inlength) {
    outincr = ((inlength/2) < (HEX_STR_LEN + 1)) ?
      HEX_STR_LEN + 1 : inlength/2;
    outsize = inlength + outincr;
  }
  else
    outsize = NOTHING_LEN + 1;

  outbuf = malloc(outsize);
  if(!outbuf)
    return NULL;

  if(!inlength) {
    msnprintf(&outbuf[0], outsize, "%s", NOTHING_STR);
    return outbuf;
  }

  for(i = 0; i<inlength; i++) {

    if(o > outsize - (HEX_STR_LEN + 1)) {
      newsize = outsize + outincr;
      newbuf = realloc(outbuf, newsize);
      if(!newbuf) {
        free(outbuf);
        return NULL;
      }
      outbuf = newbuf;
      outsize = newsize;
    }

    if((inbuf[i] > 0x20) && (inbuf[i] < 0x7F)) {
      outbuf[o] = inbuf[i];
      o++;
    }
    else {
      msnprintf(&outbuf[o], outsize - o, HEX_FMT_STR, inbuf[i]);
      o += HEX_STR_LEN;
    }

  }
  outbuf[o] = '\0';

  return outbuf;
}