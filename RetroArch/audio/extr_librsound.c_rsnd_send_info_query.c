#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  ctl_socket; } ;
struct TYPE_5__ {TYPE_1__ conn; scalar_t__ total_written; } ;
typedef  TYPE_2__ rsound_t ;

/* Variables and functions */
 int RSD_PROTO_MAXSIZE ; 
 scalar_t__ rsnd_send_chunk (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int rsnd_send_info_query(rsound_t *rd)
{
   char tmpbuf[RSD_PROTO_MAXSIZE];
   char sendbuf[RSD_PROTO_MAXSIZE];

   snprintf(tmpbuf, RSD_PROTO_MAXSIZE - 1, " INFO %lld", (long long int)rd->total_written);
   tmpbuf[RSD_PROTO_MAXSIZE - 1] = '\0';
   snprintf(sendbuf, RSD_PROTO_MAXSIZE - 1, "RSD%5d%s", (int)strlen(tmpbuf), tmpbuf);
   sendbuf[RSD_PROTO_MAXSIZE - 1] = '\0';

   if ( rsnd_send_chunk(rd->conn.ctl_socket, sendbuf, strlen(sendbuf), 0) != (ssize_t)strlen(sendbuf) )
      return -1;

   return 0;
}