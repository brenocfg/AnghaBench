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
struct TYPE_3__ {size_t name_len; char const* oid; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ x509_attr_descriptor_t ;

/* Variables and functions */
 scalar_t__ strncmp (int /*<<< orphan*/ *,char const*,size_t) ; 
 TYPE_1__* x509_attrs ; 

__attribute__((used)) static const char *x509_at_oid_from_name( const char *name, size_t name_len )
{
    const x509_attr_descriptor_t *cur;

    for( cur = x509_attrs; cur->name != NULL; cur++ )
        if( cur->name_len == name_len &&
            strncmp( cur->name, name, name_len ) == 0 )
            break;

    return( cur->oid );
}