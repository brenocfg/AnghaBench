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
typedef  int CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  curl ; 
 int curl_easy_recv (int /*<<< orphan*/ ,char*,int,size_t*) ; 
 int curl_easy_send (int /*<<< orphan*/ ,char*,size_t,size_t*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int progressCallback(void *arg,
                            double dltotal,
                            double dlnow,
                            double ultotal,
                            double ulnow)
{
  CURLcode res = 0;
  char buffer[256];
  size_t n = 0;
  (void)arg;
  (void)dltotal;
  (void)dlnow;
  (void)ultotal;
  (void)ulnow;
  res = curl_easy_recv(curl, buffer, 256, &n);
  printf("curl_easy_recv returned %d\n", res);
  res = curl_easy_send(curl, buffer, n, &n);
  printf("curl_easy_send returned %d\n", res);

  return 1;
}