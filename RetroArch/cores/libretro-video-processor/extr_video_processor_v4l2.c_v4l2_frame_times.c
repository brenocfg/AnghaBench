#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tv_sec; int tv_usec; } ;
struct v4l2_buffer {int sequence; int index; int field; TYPE_1__ timestamp; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ft_favg ; 
 int ft_fcount ; 
 int ft_ftime ; 
 char* ft_info ; 
 char* ft_info2 ; 
 TYPE_1__ ft_prevtime ; 
 TYPE_1__ ft_prevtime2 ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int,int,int,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  video_frame_times ; 

void v4l2_frame_times(struct v4l2_buffer buf) {
   if (strcmp("Off", video_frame_times) == 0)
       return;

   if (ft_info == NULL)
       ft_info = (char*)calloc(5000, sizeof(char));

   if ( (buf.timestamp.tv_sec - ft_prevtime.tv_sec >= 1) && \
        (buf.timestamp.tv_usec + 1000000 - ft_prevtime2.tv_usec) >= 1000000) {
       double csec = ((double) buf.timestamp.tv_sec) + (buf.timestamp.tv_usec/1000000);
       double psec = ((double) ft_prevtime.tv_sec) + (ft_prevtime.tv_usec/1000000);
       printf("Fields last %.2f seconds: %d\n", csec - psec, ft_fcount);
       printf("Average frame times: %.3fms\n", ft_favg/(1000*ft_fcount));
       printf("Fields timestampdiffs last second:\n%s\n", ft_info);
       free(ft_info);
       ft_info = (char*)calloc(5000, sizeof(char));
       ft_fcount = 0;
       ft_favg = 0;
       ft_prevtime = buf.timestamp;
   }
   ft_fcount++;
   ft_info2 = strdup(ft_info);
   ft_ftime = (double) (buf.timestamp.tv_usec + ((buf.timestamp.tv_sec - ft_prevtime2.tv_sec >= 1) ? 1000000 : 0)  - ft_prevtime2.tv_usec);
   ft_favg += ft_ftime;
   snprintf(ft_info, 5000 * sizeof(char), "%s %6.d %d %d %.2fms%s", ft_info2, buf.sequence, buf.index, buf.field, ft_ftime/1000, (!(ft_fcount % 7)) ? "\n" : "");
   free(ft_info2);

   ft_prevtime2 = buf.timestamp;
}