#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int member_0; int member_1; } ;
struct TYPE_10__ {int member_0; int member_1; } ;
struct TYPE_9__ {int member_0; int member_1; } ;
struct TYPE_13__ {scalar_t__ Length; scalar_t__ CheckSum; TYPE_3__ member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_5__ tt_sfnt_id_rec ;
struct TYPE_14__ {int num_tables; TYPE_4__* dir_tables; } ;
struct TYPE_12__ {int Tag; scalar_t__ Length; } ;
typedef  TYPE_6__* TT_Face ;
typedef  scalar_t__ FT_ULong ;
typedef  int /*<<< orphan*/  FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FT_MEM_SET (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
#define  TTAG_cvt 130 
#define  TTAG_fpgm 129 
#define  TTAG_prep 128 
 scalar_t__ tt_get_sfnt_checksum (TYPE_6__*,int) ; 

__attribute__((used)) static FT_Bool
  tt_check_trickyness_sfnt_ids( TT_Face  face )
  {
#define TRICK_SFNT_IDS_PER_FACE   3
#define TRICK_SFNT_IDS_NUM_FACES  5

    static const tt_sfnt_id_rec sfnt_id[TRICK_SFNT_IDS_NUM_FACES]
                                       [TRICK_SFNT_IDS_PER_FACE] = {

#define TRICK_SFNT_ID_cvt   0
#define TRICK_SFNT_ID_fpgm  1
#define TRICK_SFNT_ID_prep  2

      { /* MingLiU 1995 */
        { 0x05bcf058, 0x000002e4 }, /* cvt  */
        { 0x28233bf1, 0x000087c4 }, /* fpgm */
        { 0xa344a1ea, 0x000001e1 }  /* prep */
      },
      { /* MingLiU 1996- */
        { 0x05bcf058, 0x000002e4 }, /* cvt  */
        { 0x28233bf1, 0x000087c4 }, /* fpgm */
        { 0xa344a1eb, 0x000001e1 }  /* prep */
      },
      { /* DFKaiShu */
        { 0x11e5ead4, 0x00000350 }, /* cvt  */
        { 0x5a30ca3b, 0x00009063 }, /* fpgm */
        { 0x13a42602, 0x0000007e }  /* prep */
      },
      { /* HuaTianKaiTi */
        { 0xfffbfffc, 0x00000008 }, /* cvt  */
        { 0x9c9e48b8, 0x0000bea2 }, /* fpgm */
        { 0x70020112, 0x00000008 }  /* prep */
      },
      { /* HuaTianSongTi */
        { 0xfffbfffc, 0x00000008 }, /* cvt  */
        { 0x0a5a0483, 0x00017c39 }, /* fpgm */
        { 0x70020112, 0x00000008 }  /* prep */
      }
    };

    FT_ULong  checksum;
    int       num_matched_ids[TRICK_SFNT_IDS_NUM_FACES];
    int       i, j, k;


    FT_MEM_SET( num_matched_ids, 0,
                sizeof( int ) * TRICK_SFNT_IDS_NUM_FACES );

    for ( i = 0; i < face->num_tables; i++ )
    {
      checksum = 0;

      switch( face->dir_tables[i].Tag )
      {
      case TTAG_cvt:
        k = TRICK_SFNT_ID_cvt;
        break;

      case TTAG_fpgm:
        k = TRICK_SFNT_ID_fpgm;
        break;

      case TTAG_prep:
        k = TRICK_SFNT_ID_prep;
        break;

      default:
        continue;
      }

      for ( j = 0; j < TRICK_SFNT_IDS_NUM_FACES; j++ )
        if ( face->dir_tables[i].Length == sfnt_id[j][k].Length )
        {
          if ( !checksum )
            checksum = tt_get_sfnt_checksum( face, i );

          if ( sfnt_id[j][k].CheckSum == checksum )
            num_matched_ids[j]++;

          if ( num_matched_ids[j] == TRICK_SFNT_IDS_PER_FACE )
            return TRUE;
        }
    }

    return FALSE;
  }