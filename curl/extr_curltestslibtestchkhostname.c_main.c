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
 scalar_t__ Curl_gethostname (char*,int) ; 
 int HOSTNAME_MAX ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int main(int argc, char *argv[])
{
  char buff[HOSTNAME_MAX];
  if(argc != 2) {
    printf("Usage: %s EXPECTED_HOSTNAME\n", argv[0]);
    return 1;
  }

  if(Curl_gethostname(buff, HOSTNAME_MAX)) {
    printf("Curl_gethostname() failed\n");
    return 1;
  }

  /* compare the name returned by Curl_gethostname() with the expected one */
  if(strncmp(buff, argv[1], HOSTNAME_MAX)) {
    printf("got unexpected host name back, LD_PRELOAD failed\n");
    return 1;
  }
  return 0;
}