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
typedef  int /*<<< orphan*/  password_buf ;
struct TYPE_4__ {int entry_verified; char* password; scalar_t__ hash_algorithm; int /*<<< orphan*/  cd_verified; scalar_t__ sign_required; int /*<<< orphan*/  hash; int /*<<< orphan*/  hash_digest_size; int /*<<< orphan*/  raw; int /*<<< orphan*/  zip_handle; TYPE_2__* file_info; int /*<<< orphan*/  password_userdata; int /*<<< orphan*/  (* password_cb ) (void*,int /*<<< orphan*/ ,TYPE_2__*,char*,int) ;} ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {int flag; } ;

/* Variables and functions */
 scalar_t__ MZ_HASH_SHA1 ; 
 scalar_t__ MZ_HASH_SHA256 ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 scalar_t__ MZ_SIGN_ERROR ; 
 scalar_t__ MZ_SUPPORT_ERROR ; 
 int MZ_ZIP_FLAG_ENCRYPTED ; 
 int /*<<< orphan*/  mz_crypt_sha_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_crypt_sha_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_crypt_sha_set_algorithm (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mz_zip_entry_is_open (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_entry_read_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ mz_zip_reader_entry_get_first_hash (void*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mz_zip_reader_entry_has_sign (void*) ; 
 scalar_t__ mz_zip_reader_entry_sign_verify (void*) ; 
 scalar_t__ mz_zip_reader_is_open (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,TYPE_2__*,char*,int) ; 

int32_t mz_zip_reader_entry_open(void *handle)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    int32_t err = MZ_OK;
    const char *password = NULL;
    char password_buf[120];


    reader->entry_verified = 0;

    if (mz_zip_reader_is_open(reader) != MZ_OK)
        return MZ_PARAM_ERROR;
    if (reader->file_info == NULL)
        return MZ_PARAM_ERROR;

    /* If the entry isn't open for reading, open it */
    if (mz_zip_entry_is_open(reader->zip_handle) == MZ_OK)
        return MZ_OK;

    password = reader->password;

    /* Check if we need a password and ask for it if we need to */
    if ((reader->file_info->flag & MZ_ZIP_FLAG_ENCRYPTED) && (password == NULL) &&
        (reader->password_cb != NULL))
    {
        reader->password_cb(handle, reader->password_userdata, reader->file_info,
            password_buf, sizeof(password_buf));

        password = password_buf;
    }

    err = mz_zip_entry_read_open(reader->zip_handle, reader->raw, password);
#ifndef MZ_ZIP_NO_ENCRYPTION
    if (err != MZ_OK)
        return err;

    if (mz_zip_reader_entry_get_first_hash(handle, &reader->hash_algorithm, &reader->hash_digest_size) == MZ_OK)
    {
        mz_crypt_sha_create(&reader->hash);
        if (reader->hash_algorithm == MZ_HASH_SHA1)
            mz_crypt_sha_set_algorithm(reader->hash, MZ_HASH_SHA1);
        else if (reader->hash_algorithm == MZ_HASH_SHA256)
            mz_crypt_sha_set_algorithm(reader->hash, MZ_HASH_SHA256);
        else
            err = MZ_SUPPORT_ERROR;

        if (err == MZ_OK)
            mz_crypt_sha_begin(reader->hash);
#ifdef MZ_ZIP_SIGNING
        if (err == MZ_OK)
        {
            if (mz_zip_reader_entry_has_sign(handle) == MZ_OK)
            {
                err = mz_zip_reader_entry_sign_verify(handle);
                if (err == MZ_OK)
                    reader->entry_verified = 1;
            }
            else if (reader->sign_required && !reader->cd_verified)
                err = MZ_SIGN_ERROR;
        }
#endif
    }
    else if (reader->sign_required && !reader->cd_verified)
        err = MZ_SIGN_ERROR;
#endif

    return err;
}