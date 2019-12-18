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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  tag ;
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  HTMLSTREAMPARSER ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_FOLLOWLOCATION ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  html_parser_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * html_parser_init () ; 
 int /*<<< orphan*/  html_parser_set_attr_buffer (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  html_parser_set_attr_to_lower (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  html_parser_set_tag_buffer (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  html_parser_set_tag_to_lower (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  html_parser_set_val_buffer (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 long write_callback ; 

int main(int argc, char *argv[])
{
  char tag[1], attr[4], val[128];
  CURL *curl;
  HTMLSTREAMPARSER *hsp;

  if(argc != 2) {
    printf("Usage: %s URL\n", argv[0]);
    return EXIT_FAILURE;
  }

  curl = curl_easy_init();

  hsp = html_parser_init();

  html_parser_set_tag_to_lower(hsp, 1);
  html_parser_set_attr_to_lower(hsp, 1);
  html_parser_set_tag_buffer(hsp, tag, sizeof(tag));
  html_parser_set_attr_buffer(hsp, attr, sizeof(attr));
  html_parser_set_val_buffer(hsp, val, sizeof(val)-1);

  curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, hsp);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  curl_easy_perform(curl);

  curl_easy_cleanup(curl);

  html_parser_cleanup(hsp);

  return EXIT_SUCCESS;
}