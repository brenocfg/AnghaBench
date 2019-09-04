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
 int /*<<< orphan*/  HTML_VALUE_ENDED ; 
 int /*<<< orphan*/  html_parser_char_parse (void*,char) ; 
 scalar_t__ html_parser_cmp_attr (void*,char*,int) ; 
 scalar_t__ html_parser_cmp_tag (void*,char*,int) ; 
 scalar_t__ html_parser_is_in (void*,int /*<<< orphan*/ ) ; 
 char* html_parser_val (void*) ; 
 size_t html_parser_val_length (void*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static size_t write_callback(void *buffer, size_t size, size_t nmemb,
                             void *hsp)
{
  size_t realsize = size * nmemb, p;
  for(p = 0; p < realsize; p++) {
    html_parser_char_parse(hsp, ((char *)buffer)[p]);
    if(html_parser_cmp_tag(hsp, "a", 1))
      if(html_parser_cmp_attr(hsp, "href", 4))
        if(html_parser_is_in(hsp, HTML_VALUE_ENDED)) {
          html_parser_val(hsp)[html_parser_val_length(hsp)] = '\0';
          printf("%s\n", html_parser_val(hsp));
        }
  }
  return realsize;
}