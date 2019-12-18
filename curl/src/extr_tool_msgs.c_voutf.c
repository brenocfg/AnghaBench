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
typedef  int /*<<< orphan*/  va_list ;
struct GlobalConfig {int /*<<< orphan*/  errors; int /*<<< orphan*/  mute; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISSPACE (char) ; 
 int /*<<< orphan*/  curl_free (char*) ; 
 char* curlx_mvaprintf (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,size_t,int,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void voutf(struct GlobalConfig *config,
                  const char *prefix,
                  const char *fmt,
                  va_list ap)
{
  size_t width = (79 - strlen(prefix));
  if(!config->mute) {
    size_t len;
    char *ptr;
    char *print_buffer;

    print_buffer = curlx_mvaprintf(fmt, ap);
    if(!print_buffer)
      return;
    len = strlen(print_buffer);

    ptr = print_buffer;
    while(len > 0) {
      fputs(prefix, config->errors);

      if(len > width) {
        size_t cut = width-1;

        while(!ISSPACE(ptr[cut]) && cut) {
          cut--;
        }
        if(0 == cut)
          /* not a single cutting position was found, just cut it at the
             max text width then! */
          cut = width-1;

        (void)fwrite(ptr, cut + 1, 1, config->errors);
        fputs("\n", config->errors);
        ptr += cut + 1; /* skip the space too */
        len -= cut + 1;
      }
      else {
        fputs(ptr, config->errors);
        len = 0;
      }
    }
    curl_free(print_buffer);
  }
}