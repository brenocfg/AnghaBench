#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* buf; scalar_t__ size; } ;
typedef  TYPE_1__ memory ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 long CURLAUTH_ANY ; 
 int /*<<< orphan*/  CURLOPT_ACCEPT_ENCODING ; 
 int /*<<< orphan*/  CURLOPT_CONNECTTIMEOUT ; 
 int /*<<< orphan*/  CURLOPT_COOKIEFILE ; 
 int /*<<< orphan*/  CURLOPT_EXPECT_100_TIMEOUT_MS ; 
 int /*<<< orphan*/  CURLOPT_FILETIME ; 
 int /*<<< orphan*/  CURLOPT_FOLLOWLOCATION ; 
 int /*<<< orphan*/  CURLOPT_HTTPAUTH ; 
 int /*<<< orphan*/  CURLOPT_HTTP_VERSION ; 
 int /*<<< orphan*/  CURLOPT_MAXREDIRS ; 
 int /*<<< orphan*/  CURLOPT_PRIVATE ; 
 int /*<<< orphan*/  CURLOPT_PROXYAUTH ; 
 int /*<<< orphan*/  CURLOPT_TIMEOUT ; 
 int /*<<< orphan*/  CURLOPT_UNRESTRICTED_AUTH ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_USERAGENT ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 long CURL_HTTP_VERSION_2TLS ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 long grow_buffer ; 
 void* malloc (int) ; 

CURL *make_handle(char *url)
{
  CURL *handle = curl_easy_init();

  /* Important: use HTTP2 over HTTPS */
  curl_easy_setopt(handle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
  curl_easy_setopt(handle, CURLOPT_URL, url);

  /* buffer body */
  memory *mem = malloc(sizeof(memory));
  mem->size = 0;
  mem->buf = malloc(1);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, grow_buffer);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, mem);
  curl_easy_setopt(handle, CURLOPT_PRIVATE, mem);

  /* For completeness */
  curl_easy_setopt(handle, CURLOPT_ACCEPT_ENCODING, "");
  curl_easy_setopt(handle, CURLOPT_TIMEOUT, 5L);
  curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(handle, CURLOPT_MAXREDIRS, 10L);
  curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, 2L);
  curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "");
  curl_easy_setopt(handle, CURLOPT_FILETIME, 1L);
  curl_easy_setopt(handle, CURLOPT_USERAGENT, "mini crawler");
  curl_easy_setopt(handle, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
  curl_easy_setopt(handle, CURLOPT_UNRESTRICTED_AUTH, 1L);
  curl_easy_setopt(handle, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
  curl_easy_setopt(handle, CURLOPT_EXPECT_100_TIMEOUT_MS, 0L);
  return handle;
}