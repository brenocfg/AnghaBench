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
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void vc_uri_remove_double_dot_segments( char *path_str )
{
   char *previous_segment = path_str;
   char *slash;

   if (previous_segment[0] == '/')
      previous_segment++;

   /* Remove strings of the form "<segment>/../" (or "<segment>/.." at the end of the path)
    * as long as <segment> is not itself ".." */
   slash = strchr(previous_segment, '/');
   while (slash)
   {
      if (previous_segment[0] != '.' || previous_segment[1] != '.' || previous_segment[2] != '/')
      {
         if (slash[1] == '.' && slash[2] == '.')
         {
            bool previous_segment_removed = true;

            switch (slash[3])
            {
            case '/':   /* "/../" inside path, snip it and last segment out */
               memmove(previous_segment, slash + 4, strlen(slash + 4) + 1);
               break;
            case '\0':  /* Trailing "/.." on path, just terminate path at last segment */
               *previous_segment = '\0';
               break;
            default:    /* Not a simple ".." segment, so skip over it */
               previous_segment_removed = false;
            }

            if (previous_segment_removed)
            {
               /* The segment just removed was the first one in the path (optionally
                * prefixed by a slash), so no more can be removed: stop. */
               if (previous_segment < path_str + 2)
                  break;

               /* Move back to slash before previous segment, or the start of the path */
               slash = previous_segment - 1;
               while (--slash >= path_str && *slash != '/')
                  ; /* Everything done in the while */
            }
         }
      }
      previous_segment = slash + 1;
      slash = strchr(previous_segment, '/');
   }
}