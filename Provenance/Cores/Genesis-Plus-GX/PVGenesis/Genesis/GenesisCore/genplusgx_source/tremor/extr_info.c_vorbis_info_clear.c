#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_11__ {int modes; int maps; size_t* map_type; int floors; size_t* floor_type; int residues; size_t* residue_type; int books; struct TYPE_11__* fullbooks; scalar_t__* book_param; scalar_t__* residue_param; scalar_t__* floor_param; scalar_t__* map_param; struct TYPE_11__** mode_param; } ;
typedef  TYPE_2__ codec_setup_info ;
struct TYPE_14__ {int /*<<< orphan*/  (* free_info ) (scalar_t__) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* free_info ) (scalar_t__) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* free_info ) (scalar_t__) ;} ;

/* Variables and functions */
 TYPE_9__** _floor_P ; 
 TYPE_8__** _mapping_P ; 
 int /*<<< orphan*/  _ogg_free (TYPE_2__*) ; 
 TYPE_6__** _residue_P ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 
 int /*<<< orphan*/  vorbis_book_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  vorbis_staticbook_destroy (scalar_t__) ; 

void vorbis_info_clear(vorbis_info *vi){
  codec_setup_info     *ci=(codec_setup_info *)vi->codec_setup;
  int i;

  if(ci){

    for(i=0;i<ci->modes;i++)
      if(ci->mode_param[i])_ogg_free(ci->mode_param[i]);

    for(i=0;i<ci->maps;i++) /* unpack does the range checking */
      if(ci->map_param[i])
	_mapping_P[ci->map_type[i]]->free_info(ci->map_param[i]);

    for(i=0;i<ci->floors;i++) /* unpack does the range checking */
      if(ci->floor_param[i])
	_floor_P[ci->floor_type[i]]->free_info(ci->floor_param[i]);
    
    for(i=0;i<ci->residues;i++) /* unpack does the range checking */
      if(ci->residue_param[i])
	_residue_P[ci->residue_type[i]]->free_info(ci->residue_param[i]);

    for(i=0;i<ci->books;i++){
      if(ci->book_param[i]){
	/* knows if the book was not alloced */
	vorbis_staticbook_destroy(ci->book_param[i]);
      }
      if(ci->fullbooks)
	vorbis_book_clear(ci->fullbooks+i);
    }
    if(ci->fullbooks)
	_ogg_free(ci->fullbooks);
    
    _ogg_free(ci);
  }

  memset(vi,0,sizeof(*vi));
}