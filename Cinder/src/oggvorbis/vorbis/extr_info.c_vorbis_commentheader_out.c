#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vorbis_comment ;
struct TYPE_8__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ oggpack_buffer ;
struct TYPE_9__ {int packetno; scalar_t__ granulepos; scalar_t__ e_o_s; scalar_t__ b_o_s; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_2__ ogg_packet ;

/* Variables and functions */
 int OV_EIMPL ; 
 int /*<<< orphan*/  _ogg_malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ _vorbis_pack_comment (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oggpack_bytes (TYPE_1__*) ; 
 int /*<<< orphan*/  oggpack_writeclear (TYPE_1__*) ; 
 int /*<<< orphan*/  oggpack_writeinit (TYPE_1__*) ; 

int vorbis_commentheader_out(vorbis_comment *vc,
                                          ogg_packet *op){

  oggpack_buffer opb;

  oggpack_writeinit(&opb);
  if(_vorbis_pack_comment(&opb,vc)){
    oggpack_writeclear(&opb);
    return OV_EIMPL;
  }

  op->packet = _ogg_malloc(oggpack_bytes(&opb));
  memcpy(op->packet, opb.buffer, oggpack_bytes(&opb));

  op->bytes=oggpack_bytes(&opb);
  op->b_o_s=0;
  op->e_o_s=0;
  op->granulepos=0;
  op->packetno=1;

  oggpack_writeclear(&opb);
  return 0;
}