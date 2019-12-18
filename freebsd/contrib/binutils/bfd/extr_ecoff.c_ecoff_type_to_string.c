#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
union aux_ext {int /*<<< orphan*/  a_rndx; int /*<<< orphan*/  a_ti; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_12__ {unsigned int bt; unsigned int tq0; unsigned int tq1; unsigned int tq2; unsigned int tq3; unsigned int tq4; unsigned int tq5; scalar_t__ fBitfield; } ;
struct TYPE_8__ {union aux_ext* external_aux; } ;
struct TYPE_11__ {TYPE_1__ debug_info; } ;
struct TYPE_10__ {TYPE_7__ ti; } ;
struct TYPE_9__ {int iauxBase; int fBigendian; } ;
typedef  int /*<<< orphan*/  RNDXR ;
typedef  TYPE_2__ FDR ;
typedef  TYPE_3__ AUXU ;

/* Variables and functions */
 int AUX_GET_DNHIGH (int,union aux_ext*) ; 
 int AUX_GET_DNLOW (int,union aux_ext*) ; 
 scalar_t__ AUX_GET_ISYM (int,union aux_ext*) ; 
 void* AUX_GET_WIDTH (int,union aux_ext*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _bfd_ecoff_swap_rndx_in (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_ecoff_swap_tir_in (int,int /*<<< orphan*/ *,TYPE_7__*) ; 
#define  btAdr 161 
#define  btBit 160 
#define  btChar 159 
#define  btComplex 158 
#define  btDComplex 157 
#define  btDouble 156 
#define  btEnum 155 
#define  btFixedDec 154 
#define  btFloat 153 
#define  btFloatDec 152 
#define  btIndirect 151 
#define  btInt 150 
#define  btLong 149 
#define  btNil 148 
#define  btPicture 147 
#define  btRange 146 
#define  btSet 145 
#define  btShort 144 
#define  btString 143 
#define  btStruct 142 
#define  btTypedef 141 
#define  btUChar 140 
#define  btUInt 139 
#define  btULong 138 
#define  btUShort 137 
#define  btUnion 136 
#define  btVoid 135 
 TYPE_6__* ecoff_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecoff_emit_aggregate (int /*<<< orphan*/ *,TYPE_2__*,char*,int /*<<< orphan*/ *,long,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
#define  tqArray 134 
#define  tqFar 133 
#define  tqMax 132 
#define  tqNil 131 
#define  tqProc 130 
#define  tqPtr 129 
#define  tqVol 128 

__attribute__((used)) static char *
ecoff_type_to_string (bfd *abfd, FDR *fdr, unsigned int indx)
{
  union aux_ext *aux_ptr;
  int bigendian;
  AUXU u;
  struct qual
  {
    unsigned int  type;
    int  low_bound;
    int  high_bound;
    int  stride;
  } qualifiers[7];
  unsigned int basic_type;
  int i;
  char buffer1[1024];
  static char buffer2[1024];
  char *p1 = buffer1;
  char *p2 = buffer2;
  RNDXR rndx;

  aux_ptr = ecoff_data (abfd)->debug_info.external_aux + fdr->iauxBase;
  bigendian = fdr->fBigendian;

  for (i = 0; i < 7; i++)
    {
      qualifiers[i].low_bound = 0;
      qualifiers[i].high_bound = 0;
      qualifiers[i].stride = 0;
    }

  if (AUX_GET_ISYM (bigendian, &aux_ptr[indx]) == (bfd_vma) -1)
    return "-1 (no type)";
  _bfd_ecoff_swap_tir_in (bigendian, &aux_ptr[indx++].a_ti, &u.ti);

  basic_type = u.ti.bt;
  qualifiers[0].type = u.ti.tq0;
  qualifiers[1].type = u.ti.tq1;
  qualifiers[2].type = u.ti.tq2;
  qualifiers[3].type = u.ti.tq3;
  qualifiers[4].type = u.ti.tq4;
  qualifiers[5].type = u.ti.tq5;
  qualifiers[6].type = tqNil;

  /* Go get the basic type.  */
  switch (basic_type)
    {
    case btNil:			/* Undefined.  */
      strcpy (p1, "nil");
      break;

    case btAdr:			/* Address - integer same size as pointer.  */
      strcpy (p1, "address");
      break;

    case btChar:		/* Character.  */
      strcpy (p1, "char");
      break;

    case btUChar:		/* Unsigned character.  */
      strcpy (p1, "unsigned char");
      break;

    case btShort:		/* Short.  */
      strcpy (p1, "short");
      break;

    case btUShort:		/* Unsigned short.  */
      strcpy (p1, "unsigned short");
      break;

    case btInt:			/* Int.  */
      strcpy (p1, "int");
      break;

    case btUInt:		/* Unsigned int.  */
      strcpy (p1, "unsigned int");
      break;

    case btLong:		/* Long.  */
      strcpy (p1, "long");
      break;

    case btULong:		/* Unsigned long.  */
      strcpy (p1, "unsigned long");
      break;

    case btFloat:		/* Float (real).  */
      strcpy (p1, "float");
      break;

    case btDouble:		/* Double (real).  */
      strcpy (p1, "double");
      break;

      /* Structures add 1-2 aux words:
	 1st word is [ST_RFDESCAPE, offset] pointer to struct def;
	 2nd word is file index if 1st word rfd is ST_RFDESCAPE.  */

    case btStruct:		/* Structure (Record).  */
      _bfd_ecoff_swap_rndx_in (bigendian, &aux_ptr[indx].a_rndx, &rndx);
      ecoff_emit_aggregate (abfd, fdr, p1, &rndx,
			    (long) AUX_GET_ISYM (bigendian, &aux_ptr[indx+1]),
			    "struct");
      indx++;			/* Skip aux words.  */
      break;

      /* Unions add 1-2 aux words:
	 1st word is [ST_RFDESCAPE, offset] pointer to union def;
	 2nd word is file index if 1st word rfd is ST_RFDESCAPE.  */

    case btUnion:		/* Union.  */
      _bfd_ecoff_swap_rndx_in (bigendian, &aux_ptr[indx].a_rndx, &rndx);
      ecoff_emit_aggregate (abfd, fdr, p1, &rndx,
			    (long) AUX_GET_ISYM (bigendian, &aux_ptr[indx+1]),
			    "union");
      indx++;			/* Skip aux words.  */
      break;

      /* Enumerations add 1-2 aux words:
	 1st word is [ST_RFDESCAPE, offset] pointer to enum def;
	 2nd word is file index if 1st word rfd is ST_RFDESCAPE.  */

    case btEnum:		/* Enumeration.  */
      _bfd_ecoff_swap_rndx_in (bigendian, &aux_ptr[indx].a_rndx, &rndx);
      ecoff_emit_aggregate (abfd, fdr, p1, &rndx,
			    (long) AUX_GET_ISYM (bigendian, &aux_ptr[indx+1]),
			    "enum");
      indx++;			/* Skip aux words.  */
      break;

    case btTypedef:		/* Defined via a typedef, isymRef points.  */
      strcpy (p1, "typedef");
      break;

    case btRange:		/* Subrange of int.  */
      strcpy (p1, "subrange");
      break;

    case btSet:			/* Pascal sets.  */
      strcpy (p1, "set");
      break;

    case btComplex:		/* Fortran complex.  */
      strcpy (p1, "complex");
      break;

    case btDComplex:		/* Fortran double complex.  */
      strcpy (p1, "double complex");
      break;

    case btIndirect:		/* Forward or unnamed typedef.  */
      strcpy (p1, "forward/unamed typedef");
      break;

    case btFixedDec:		/* Fixed Decimal.  */
      strcpy (p1, "fixed decimal");
      break;

    case btFloatDec:		/* Float Decimal.  */
      strcpy (p1, "float decimal");
      break;

    case btString:		/* Varying Length Character String.  */
      strcpy (p1, "string");
      break;

    case btBit:			/* Aligned Bit String.  */
      strcpy (p1, "bit");
      break;

    case btPicture:		/* Picture.  */
      strcpy (p1, "picture");
      break;

    case btVoid:		/* Void.  */
      strcpy (p1, "void");
      break;

    default:
      sprintf (p1, _("Unknown basic type %d"), (int) basic_type);
      break;
    }

  p1 += strlen (buffer1);

  /* If this is a bitfield, get the bitsize.  */
  if (u.ti.fBitfield)
    {
      int bitsize;

      bitsize = AUX_GET_WIDTH (bigendian, &aux_ptr[indx++]);
      sprintf (p1, " : %d", bitsize);
      p1 += strlen (buffer1);
    }

  /* Deal with any qualifiers.  */
  if (qualifiers[0].type != tqNil)
    {
      /* Snarf up any array bounds in the correct order.  Arrays
         store 5 successive words in the aux. table:
        	word 0	RNDXR to type of the bounds (ie, int)
        	word 1	Current file descriptor index
        	word 2	low bound
        	word 3	high bound (or -1 if [])
        	word 4	stride size in bits.  */
      for (i = 0; i < 7; i++)
	{
	  if (qualifiers[i].type == tqArray)
	    {
	      qualifiers[i].low_bound =
		AUX_GET_DNLOW (bigendian, &aux_ptr[indx+2]);
	      qualifiers[i].high_bound =
		AUX_GET_DNHIGH (bigendian, &aux_ptr[indx+3]);
	      qualifiers[i].stride =
		AUX_GET_WIDTH (bigendian, &aux_ptr[indx+4]);
	      indx += 5;
	    }
	}

      /* Now print out the qualifiers.  */
      for (i = 0; i < 6; i++)
	{
	  switch (qualifiers[i].type)
	    {
	    case tqNil:
	    case tqMax:
	      break;

	    case tqPtr:
	      strcpy (p2, "ptr to ");
	      p2 += sizeof ("ptr to ")-1;
	      break;

	    case tqVol:
	      strcpy (p2, "volatile ");
	      p2 += sizeof ("volatile ")-1;
	      break;

	    case tqFar:
	      strcpy (p2, "far ");
	      p2 += sizeof ("far ")-1;
	      break;

	    case tqProc:
	      strcpy (p2, "func. ret. ");
	      p2 += sizeof ("func. ret. ");
	      break;

	    case tqArray:
	      {
		int first_array = i;
		int j;

		/* Print array bounds reversed (ie, in the order the C
		   programmer writes them).  C is such a fun language....  */
		while (i < 5 && qualifiers[i+1].type == tqArray)
		  i++;

		for (j = i; j >= first_array; j--)
		  {
		    strcpy (p2, "array [");
		    p2 += sizeof ("array [")-1;
		    if (qualifiers[j].low_bound != 0)
		      sprintf (p2,
			       "%ld:%ld {%ld bits}",
			       (long) qualifiers[j].low_bound,
			       (long) qualifiers[j].high_bound,
			       (long) qualifiers[j].stride);

		    else if (qualifiers[j].high_bound != -1)
		      sprintf (p2,
			       "%ld {%ld bits}",
			       (long) (qualifiers[j].high_bound + 1),
			       (long) (qualifiers[j].stride));

		    else
		      sprintf (p2, " {%ld bits}", (long) (qualifiers[j].stride));

		    p2 += strlen (p2);
		    strcpy (p2, "] of ");
		    p2 += sizeof ("] of ")-1;
		  }
	      }
	      break;
	    }
	}
    }

  strcpy (p2, buffer1);
  return buffer2;
}