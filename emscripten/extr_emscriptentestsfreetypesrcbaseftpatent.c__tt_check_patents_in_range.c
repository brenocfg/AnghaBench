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
struct TYPE_3__ {int* cursor; } ;
typedef  int FT_ULong ;
typedef  TYPE_1__* FT_Stream ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int* FT_Bytes ;
typedef  int /*<<< orphan*/  FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FT_FRAME_ENTER (int) ; 
 int /*<<< orphan*/  FT_FRAME_EXIT () ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static FT_Bool
  _tt_check_patents_in_range( FT_Stream  stream,
                              FT_ULong   size )
  {
    FT_Bool   result = FALSE;
    FT_Error  error;
    FT_Bytes  p, end;


    if ( FT_FRAME_ENTER( size ) )
      return 0;

    p   = stream->cursor;
    end = p + size;

    while ( p < end )
    {
      switch (p[0])
      {
      case 0x06:  /* SPvTL // */
      case 0x07:  /* SPvTL +  */
      case 0x08:  /* SFvTL // */
      case 0x09:  /* SFvTL +  */
      case 0x0A:  /* SPvFS    */
      case 0x0B:  /* SFvFS    */
        result = TRUE;
        goto Exit;

      case 0x40:
        if ( p + 1 >= end )
          goto Exit;

        p += p[1] + 2;
        break;

      case 0x41:
        if ( p + 1 >= end )
          goto Exit;

        p += p[1] * 2 + 2;
        break;

      case 0x71:  /* DELTAP2 */
      case 0x72:  /* DELTAP3 */
      case 0x73:  /* DELTAC0 */
      case 0x74:  /* DELTAC1 */
      case 0x75:  /* DELTAC2 */
        result = TRUE;
        goto Exit;

      case 0xB0:
      case 0xB1:
      case 0xB2:
      case 0xB3:
      case 0xB4:
      case 0xB5:
      case 0xB6:
      case 0xB7:
        p += ( p[0] - 0xB0 ) + 2;
        break;

      case 0xB8:
      case 0xB9:
      case 0xBA:
      case 0xBB:
      case 0xBC:
      case 0xBD:
      case 0xBE:
      case 0xBF:
        p += ( p[0] - 0xB8 ) * 2 + 3;
        break;

      default:
        p += 1;
        break;
      }
    }

  Exit:
    FT_UNUSED( error );
    FT_FRAME_EXIT();
    return result;
  }