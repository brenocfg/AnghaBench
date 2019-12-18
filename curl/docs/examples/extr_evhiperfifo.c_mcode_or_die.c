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
typedef  scalar_t__ CURLMcode ;

/* Variables and functions */
#define  CURLM_BAD_EASY_HANDLE 134 
#define  CURLM_BAD_HANDLE 133 
#define  CURLM_BAD_SOCKET 132 
#define  CURLM_INTERNAL_ERROR 131 
#define  CURLM_LAST 130 
 scalar_t__ CURLM_OK ; 
#define  CURLM_OUT_OF_MEMORY 129 
#define  CURLM_UNKNOWN_OPTION 128 
 int /*<<< orphan*/  MSG_OUT ; 
 int /*<<< orphan*/  exit (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 

__attribute__((used)) static void mcode_or_die(const char *where, CURLMcode code)
{
  if(CURLM_OK != code) {
    const char *s;
    switch(code) {
    case CURLM_BAD_HANDLE:
      s = "CURLM_BAD_HANDLE";
      break;
    case CURLM_BAD_EASY_HANDLE:
      s = "CURLM_BAD_EASY_HANDLE";
      break;
    case CURLM_OUT_OF_MEMORY:
      s = "CURLM_OUT_OF_MEMORY";
      break;
    case CURLM_INTERNAL_ERROR:
      s = "CURLM_INTERNAL_ERROR";
      break;
    case CURLM_UNKNOWN_OPTION:
      s = "CURLM_UNKNOWN_OPTION";
      break;
    case CURLM_LAST:
      s = "CURLM_LAST";
      break;
    default:
      s = "CURLM_unknown";
      break;
    case CURLM_BAD_SOCKET:
      s = "CURLM_BAD_SOCKET";
      fprintf(MSG_OUT, "ERROR: %s returns %s\n", where, s);
      /* ignore this error */
      return;
    }
    fprintf(MSG_OUT, "ERROR: %s returns %s\n", where, s);
    exit(code);
  }
}