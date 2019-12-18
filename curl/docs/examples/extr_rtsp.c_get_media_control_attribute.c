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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,char*) ; 

__attribute__((used)) static void get_media_control_attribute(const char *sdp_filename,
                                        char *control)
{
  int max_len = 256;
  char *s = malloc(max_len);
  FILE *sdp_fp = fopen(sdp_filename, "rb");
  control[0] = '\0';
  if(sdp_fp != NULL) {
    while(fgets(s, max_len - 2, sdp_fp) != NULL) {
      sscanf(s, " a = control: %s", control);
    }
    fclose(sdp_fp);
  }
  free(s);
}