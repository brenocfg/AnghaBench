#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * FT_Service_MultiMasters ;
typedef  int /*<<< orphan*/  FT_Face ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Invalid_Argument ; 
 int /*<<< orphan*/  FT_Err_Invalid_Face_Handle ; 
 int /*<<< orphan*/  FT_Err_Ok ; 
 int /*<<< orphan*/  FT_FACE_LOOKUP_SERVICE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_HAS_MULTIPLE_MASTERS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MULTI_MASTERS ; 

__attribute__((used)) static FT_Error
  ft_face_get_mm_service( FT_Face                   face,
                          FT_Service_MultiMasters  *aservice )
  {
    FT_Error  error;


    *aservice = NULL;

    if ( !face )
      return FT_Err_Invalid_Face_Handle;

    error = FT_Err_Invalid_Argument;

    if ( FT_HAS_MULTIPLE_MASTERS( face ) )
    {
      FT_FACE_LOOKUP_SERVICE( face,
                              *aservice,
                              MULTI_MASTERS );

      if ( *aservice )
        error = FT_Err_Ok;
    }

    return error;
  }