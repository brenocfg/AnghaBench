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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  CborValue ;
typedef  int /*<<< orphan*/  CborParser ;
typedef  int /*<<< orphan*/  CborEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  cbor_encode_boolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cbor_encode_float (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cbor_encode_simple_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cbor_encode_text_stringz (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cbor_encode_uint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cbor_encode_undefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cbor_encoder_close_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cbor_encoder_create_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cbor_encoder_create_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cbor_encoder_get_buffer_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cbor_encoder_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbor_parser_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cbor_value_to_json (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  example_dump_cbor_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stdout ; 

void app_main(void)
{
    CborEncoder root_encoder;
    CborParser root_parser;
    CborValue it;
    uint8_t buf[100];

    // Initialize the outermost cbor encoder
    cbor_encoder_init(&root_encoder, buf, sizeof(buf), 0);

    // Create an array containing several items
    CborEncoder array_encoder;
    CborEncoder map_encoder;
    cbor_encoder_create_array(&root_encoder, &array_encoder, 5); // [
    // 1. Create a map containing several pairs
    cbor_encoder_create_map(&array_encoder, &map_encoder, 3); // {
    // chip:esp32
    cbor_encode_text_stringz(&map_encoder, "chip");
    cbor_encode_text_stringz(&map_encoder, "esp32");
    // unicore:false
    cbor_encode_text_stringz(&map_encoder, "unicore");
    cbor_encode_boolean(&map_encoder, false);
    // ip:[192,168,1,100]
    cbor_encode_text_stringz(&map_encoder, "ip");
    CborEncoder array2;
    cbor_encoder_create_array(&map_encoder, &array2, 4); // [
    // Encode several numbers
    cbor_encode_uint(&array2, 192);
    cbor_encode_uint(&array2, 168);
    cbor_encode_uint(&array2, 1);
    cbor_encode_uint(&array2, 100);
    cbor_encoder_close_container(&map_encoder, &array2);        // ]
    cbor_encoder_close_container(&array_encoder, &map_encoder); // }
    // 2. Encode float number
    cbor_encode_float(&array_encoder, 3.14);
    // 3. Encode simple value
    cbor_encode_simple_value(&array_encoder, 99);
    // 4. Encode a string
    cbor_encode_text_stringz(&array_encoder, "2019-07-10 09:00:00+0000");
    // 5. Encode a undefined value
    cbor_encode_undefined(&array_encoder);
    cbor_encoder_close_container(&root_encoder, &array_encoder); // ]

    // If error happend when encoding, then this value should be meaningless
    ESP_LOGI(TAG, "encoded buffer size %d", cbor_encoder_get_buffer_size(&root_encoder, buf));

    // Initialize the cbor parser and the value iterator
    cbor_parser_init(buf, sizeof(buf), 0, &root_parser, &it);

    ESP_LOGI(TAG, "convert CBOR to JSON");
    // Dump the values in JSON format
    cbor_value_to_json(stdout, &it, 0);
    puts("");

    ESP_LOGI(TAG, "decode CBOR manually");
    // Decode CBOR data manully
    example_dump_cbor_buffer(&it, 0);
}