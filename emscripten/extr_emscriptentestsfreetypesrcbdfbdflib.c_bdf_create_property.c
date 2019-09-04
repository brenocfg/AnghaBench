#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int format; scalar_t__ name; scalar_t__ builtin; } ;
typedef  TYPE_1__ bdf_property_t ;
struct TYPE_7__ {int nuser_props; int /*<<< orphan*/  proptbl; TYPE_1__* user_props; int /*<<< orphan*/  memory; } ;
typedef  TYPE_2__ bdf_font_t ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ BDF_Err_Invalid_Argument ; 
 scalar_t__ BDF_Err_Ok ; 
 int /*<<< orphan*/  FT_MEM_COPY (char*,char*,size_t) ; 
 scalar_t__ FT_NEW_ARRAY (scalar_t__,size_t) ; 
 scalar_t__ FT_RENEW_ARRAY (TYPE_1__*,int,int) ; 
 size_t FT_ULONG_MAX ; 
 int /*<<< orphan*/  FT_ZERO (TYPE_1__*) ; 
 size_t _num_bdf_properties ; 
 int ft_strlen (char*) ; 
 scalar_t__ hash_insert (scalar_t__,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_lookup (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static FT_Error
  bdf_create_property( char*        name,
                       int          format,
                       bdf_font_t*  font )
  {
    size_t           n;
    bdf_property_t*  p;
    FT_Memory        memory = font->memory;
    FT_Error         error = BDF_Err_Ok;


    /* First check to see if the property has      */
    /* already been added or not.  If it has, then */
    /* simply ignore it.                           */
    if ( hash_lookup( name, &(font->proptbl) ) )
      goto Exit;

    if ( FT_RENEW_ARRAY( font->user_props,
                         font->nuser_props,
                         font->nuser_props + 1 ) )
      goto Exit;

    p = font->user_props + font->nuser_props;
    FT_ZERO( p );

    n = ft_strlen( name ) + 1;
    if ( n > FT_ULONG_MAX )
      return BDF_Err_Invalid_Argument;

    if ( FT_NEW_ARRAY( p->name, n ) )
      goto Exit;

    FT_MEM_COPY( (char *)p->name, name, n );

    p->format  = format;
    p->builtin = 0;

    n = _num_bdf_properties + font->nuser_props;

    error = hash_insert( p->name, n, &(font->proptbl), memory );
    if ( error )
      goto Exit;

    font->nuser_props++;

  Exit:
    return error;
  }