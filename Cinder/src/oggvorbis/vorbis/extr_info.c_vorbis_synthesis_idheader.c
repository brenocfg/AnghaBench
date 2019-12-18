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
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_3__ {int /*<<< orphan*/  b_o_s; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_1__ ogg_packet ;

/* Variables and functions */
 int /*<<< orphan*/  _v_readstring (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int oggpack_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oggpack_readinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vorbis_synthesis_idheader(ogg_packet *op){
  oggpack_buffer opb;
  char buffer[6];

  if(op){
    oggpack_readinit(&opb,op->packet,op->bytes);

    if(!op->b_o_s)
      return(0); /* Not the initial packet */

    if(oggpack_read(&opb,8) != 1)
      return 0; /* not an ID header */

    memset(buffer,0,6);
    _v_readstring(&opb,buffer,6);
    if(memcmp(buffer,"vorbis",6))
      return 0; /* not vorbis */

    return 1;
  }

  return 0;
}