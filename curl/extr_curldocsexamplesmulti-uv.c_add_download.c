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
typedef  char const FILE ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_PRIVATE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  curl_handle ; 
 int /*<<< orphan*/  curl_multi_add_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void add_download(const char *url, int num)
{
  char filename[50];
  FILE *file;
  CURL *handle;

  snprintf(filename, 50, "%d.download", num);

  file = fopen(filename, "wb");
  if(!file) {
    fprintf(stderr, "Error opening %s\n", filename);
    return;
  }

  handle = curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
  curl_easy_setopt(handle, CURLOPT_PRIVATE, file);
  curl_easy_setopt(handle, CURLOPT_URL, url);
  curl_multi_add_handle(curl_handle, handle);
  fprintf(stderr, "Added download %s -> %s\n", url, filename);
}