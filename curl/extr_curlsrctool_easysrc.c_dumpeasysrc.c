#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct curl_slist {char const* data; struct curl_slist* next; } ;
struct GlobalConfig {char* libcurl; } ;
struct TYPE_8__ {struct curl_slist* first; } ;
struct TYPE_7__ {struct curl_slist* first; } ;
struct TYPE_6__ {struct curl_slist* first; } ;
struct TYPE_5__ {struct curl_slist* first; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FOPEN_WRITETEXT ; 
 int TRUE ; 
 TYPE_4__* easysrc_clean ; 
 TYPE_3__* easysrc_code ; 
 TYPE_2__* easysrc_data ; 
 TYPE_1__* easysrc_decl ; 
 int /*<<< orphan*/  easysrc_free () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char** srcend ; 
 char** srchead ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  warnf (struct GlobalConfig*,char*,char*) ; 

void dumpeasysrc(struct GlobalConfig *config)
{
  struct curl_slist *ptr;
  char *o = config->libcurl;

  FILE *out;
  bool fopened = FALSE;
  if(strcmp(o, "-")) {
    out = fopen(o, FOPEN_WRITETEXT);
    fopened = TRUE;
  }
  else
    out = stdout;
  if(!out)
    warnf(config, "Failed to open %s to write libcurl code!\n", o);
  else {
    int i;
    const char *c;

    for(i = 0; ((c = srchead[i]) != NULL); i++)
      fprintf(out, "%s\n", c);

    /* Declare variables used for complex setopt values */
    if(easysrc_decl) {
      for(ptr = easysrc_decl->first; ptr; ptr = ptr->next)
        fprintf(out, "  %s\n", ptr->data);
    }

    /* Set up complex values for setopt calls */
    if(easysrc_data) {
      fprintf(out, "\n");

      for(ptr = easysrc_data->first; ptr; ptr = ptr->next)
        fprintf(out, "  %s\n", ptr->data);
    }

    fprintf(out, "\n");
    if(easysrc_code) {
      for(ptr = easysrc_code->first; ptr; ptr = ptr->next) {
        if(ptr->data[0]) {
          fprintf(out, "  %s\n", ptr->data);
        }
        else {
          fprintf(out, "\n");
        }
      }
    }

    if(easysrc_clean) {
      for(ptr = easysrc_clean->first; ptr; ptr = ptr->next)
        fprintf(out, "  %s\n", ptr->data);
    }

    for(i = 0; ((c = srcend[i]) != NULL); i++)
      fprintf(out, "%s\n", c);

    if(fopened)
      fclose(out);
  }

  easysrc_free();
}