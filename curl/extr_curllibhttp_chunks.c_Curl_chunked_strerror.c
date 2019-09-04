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
typedef  int CHUNKcode ;

/* Variables and functions */
#define  CHUNKE_BAD_CHUNK 133 
#define  CHUNKE_BAD_ENCODING 132 
#define  CHUNKE_ILLEGAL_HEX 131 
#define  CHUNKE_OUT_OF_MEMORY 130 
#define  CHUNKE_TOO_LONG_HEX 129 
#define  CHUNKE_WRITE_ERROR 128 

const char *Curl_chunked_strerror(CHUNKcode code)
{
  switch(code) {
  default:
    return "OK";
  case CHUNKE_TOO_LONG_HEX:
    return "Too long hexadecimal number";
  case CHUNKE_ILLEGAL_HEX:
    return "Illegal or missing hexadecimal sequence";
  case CHUNKE_BAD_CHUNK:
    return "Malformed encoding found";
  case CHUNKE_WRITE_ERROR:
    return "Write error";
  case CHUNKE_BAD_ENCODING:
    return "Bad content-encoding found";
  case CHUNKE_OUT_OF_MEMORY:
    return "Out of memory";
  }
}